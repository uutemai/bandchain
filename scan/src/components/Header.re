module Styles = {
  open Css;

  let header =
    style([
      paddingTop(Spacing.lg),
      backgroundColor(Colors.white),
      borderBottom(`px(2), `solid, Colors.blueGray1),
      zIndex(3),
      Media.mobile([
        padding(Spacing.md),
        marginBottom(`zero),
        position(`sticky),
        top(`zero),
        width(`percent(100.)),
      ]),
    ]);

  let leftContainer = style([display(`flex), alignItems(`center), width(`percent(100.))]);
  let bandLogo = style([width(`px(40)), Media.mobile([width(`px(34))])]);
  let twitterLogo = style([width(`px(15))]);
  let telegramLogo = style([width(`px(15))]);
  let cmcLogo = style([width(`px(17))]);

  let socialLink = style([marginLeft(`px(10))]);

  let link = style([cursor(`pointer)]);
};

module LinkToHome = {
  [@react.component]
  let make = (~children) => {
    <Link className=Styles.link route=Route.HomePage> children </Link>;
  };
};

module DesktopRender = {
  [@react.component]
  let make = () => {
    <header className=Styles.header>
      <div className="container">
        <Row.Grid alignItems=Row.Center marginBottom=12>
          <Col.Grid col=Col.Five>
            <div className=Styles.leftContainer>
              <LinkToHome> <img src=Images.bandLogo className=Styles.bandLogo /> </LinkToHome>
              <HSpacing size=Spacing.md />
              <div className={CssHelper.flexBox(~direction=`column, ~align=`flexStart, ())}>
                <LinkToHome>
                  <Text
                    value="BandChain"
                    size=Text.Xxl
                    weight=Text.Bold
                    nowrap=true
                    color=Colors.gray8
                    spacing={Text.Em(0.05)}
                  />
                </LinkToHome>
                <VSpacing size=Spacing.xs />
                <div className={CssHelper.flexBox()}>
                  <LinkToHome>
                    <Text
                      value="CosmoScan"
                      nowrap=true
                      size=Text.Sm
                      weight=Text.Semibold
                      color=Colors.gray6
                      spacing={Text.Em(0.03)}
                    />
                    <HSpacing size=Spacing.xs />
                  </LinkToHome>
                  <HSpacing size=Spacing.xs />
                  <ChainIDBadge />
                  <a
                    href="https://twitter.com/bandprotocol"
                    target="_blank"
                    rel="noopener"
                    className=Styles.socialLink>
                    <img src=Images.twitterLogo className=Styles.twitterLogo />
                  </a>
                  <a
                    href="https://t.me/bandprotocol"
                    target="_blank"
                    rel="noopener"
                    className=Styles.socialLink>
                    <img src=Images.telegramLogo className=Styles.telegramLogo />
                  </a>
                  <a
                    href="https://coinmarketcap.com/currencies/band-protocol/"
                    target="_blank"
                    rel="noopener"
                    className=Styles.socialLink>
                    <img src=Images.cmcLogo className=Styles.telegramLogo />
                  </a>
                </div>
              </div>
            </div>
          </Col.Grid>
          <Col.Grid col=Col.Seven> <SearchBar /> </Col.Grid>
        </Row.Grid>
        <Row.Grid alignItems=Row.Center>
          <Col.Grid col=Col.Eight> <NavBar /> </Col.Grid>
          <Col.Grid col=Col.Four> <UserAccount /> </Col.Grid>
        </Row.Grid>
      </div>
    </header>;
  };
};

module MobileRender = {
  [@react.component]
  let make = () => {
    <header className=Styles.header>
      <Row.Grid>
        <Col.Grid colSm=Col.Five>
          <div className={CssHelper.flexBox(~wrap=`nowrap, ())}>
            <LinkToHome> <img src=Images.bandLogo className=Styles.bandLogo /> </LinkToHome>
            <HSpacing size=Spacing.sm />
            <LinkToHome>
              <div className={CssHelper.flexBox(~direction=`column, ~align=`flexStart, ())}>
                <Text
                  value="BandChain"
                  size=Text.Lg
                  weight=Text.Bold
                  nowrap=true
                  color=Colors.gray8
                  spacing={Text.Em(0.05)}
                />
                <VSpacing size=Spacing.xs />
                <Text
                  value="CosmoScan"
                  nowrap=true
                  size=Text.Sm
                  color=Colors.gray6
                  spacing={Text.Em(0.03)}
                />
              </div>
            </LinkToHome>
          </div>
        </Col.Grid>
        <Col.Grid colSm=Col.Seven>
          <div className={CssHelper.flexBox(~justify=`flexEnd, ())}>
            <ChainIDBadge />
            <NavBar />
          </div>
        </Col.Grid>
      </Row.Grid>
    </header>;
  };
};

[@react.component]
let make = () => {
  Media.isMobile() ? <MobileRender /> : <DesktopRender />;
};