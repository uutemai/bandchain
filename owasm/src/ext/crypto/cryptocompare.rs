use crate::core::{Oracle, ShellCmd};
use crate::ext::crypto::coins::Coins;

pub static BITCOIN: &str = "BTC";
pub static ETHEREUM: &str = "ETH";

pub struct Price {
    symbol: String,
}

pub struct Volume24h {
    symbol: String,
}

impl Volume24h {
    pub fn new(coin: &Coins) -> Volume24h {
        Volume24h {
            symbol: String::from(match coin {
                Coins::BTC => "BTC",
                Coins::ETH => "ETH",
                Coins::BAND => "BAND",
            }),
        }
    }
}

impl Price {
    pub fn new(coin: &Coins) -> Price {
        Price {
            symbol: String::from(match coin {
                Coins::BTC => "BTC",
                Coins::ETH => "ETH",
                Coins::BAND => "BAND",
            }),
        }
    }
}

impl Oracle for Price {
    type T = f32;

    fn as_cmd(&self) -> ShellCmd {
        ShellCmd::new(
            "curl",
            &[format!(
                "https://min-api.cryptocompare.com/data/price?fsym={}&tsyms=USD",
                &self.symbol
            )],
        )
    }

    fn from_cmd_output(&self, output: String) -> Option<f32> {
        let parsed = json::parse(&output).ok()?;
        parsed["USD"].as_f32()
    }
}

impl Oracle for Volume24h {
    type T = f64;

    fn as_cmd(&self) -> ShellCmd {
        ShellCmd::new(
            "curl",
            &[format!(
                "https://min-api.cryptocompare.com/data/symbol/histoday?fsym={}&tsym=USD&limit=1",
                &self.symbol
            )],
        )
    }

    fn from_cmd_output(&self, output: String) -> Option<f64> {
        let parsed = json::parse(&output).ok()?;
        parsed["Data"][0]["total_volume_total"].as_f64()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_as_cmd() {
        assert_eq!(
            Price::new(&Coins::BTC).as_cmd(),
            ShellCmd::new(
                "curl",
                &["https://min-api.cryptocompare.com/data/price?fsym=BTC&tsyms=USD"]
            )
        );

        assert_eq!(
            Volume24h::new(&Coins::BTC).as_cmd(),
            ShellCmd::new(
                "curl",
                &["https://min-api.cryptocompare.com/data/symbol/histoday?fsym=BTC&tsym=USD&limit=1"]
            )
        );
    }

    #[test]
    fn test_from_cmd_ok() {
        assert_eq!(Price::new(&Coins::BTC).from_cmd_output(r#"{"USD":100.0}"#.into()), Some(100.0));

        assert_eq!(Volume24h::new(&Coins::BTC).from_cmd_output(r#"{"Type":100,"Message":"Got the data","Data":[{"time":1579651200,"top_tier_volume_quote":566229755.64,"top_tier_volume_base":1185119009.52,"top_tier_volume_total":1751348765.16,"cccagg_volume_quote":1326822903.45,"cccagg_volume_base":1759708250.75,"cccagg_volume_total":3086531154.21,"total_volume_quote":5300407902.57,"total_volume_base":10630451853.93,"total_volume_total":15930859756.51},{"time":1579737600,"top_tier_volume_quote":1505493.13,"top_tier_volume_base":1975473.77,"top_tier_volume_total":3480880.51,"cccagg_volume_quote":472.66,"cccagg_volume_base":517.32,"cccagg_volume_total":990.07,"total_volume_quote":13277212.26,"total_volume_base":26554510.91,"total_volume_total":39831809.57}],"TimeFrom":1579651200,"TimeTo":1579737600,"FirstValueInArray":true,"ConversionType":"direct","RateLimit":{},"HasWarning":false}"#.into()),
         Some(15930859756.51)
        );
    }

    #[test]
    fn test_from_cmd_not_ok() {
        assert_eq!(Price::new(&Coins::BTC).from_cmd_output(r#"{}"#.into()), None);

        assert_eq!(Volume24h::new(&Coins::BTC).from_cmd_output(r#"{}"#.into()), None);
    }
}
