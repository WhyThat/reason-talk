module Style = {
  open Emotion;
  let header = [%css
    [
      alignItems(`center),
      width(`pct(100.)),
      display(`flex),
      color(`hex("fff")),
      height(`px(40)),
      padding(px(10)),
      backgroundColor(`rgba((43, 43, 43, 0.75))),
    ]
  ];
  let logo = [%css [height(`px(40))]];
  let title = [%css [margin(`auto)]];
};
[@gentype]
[@react.component]
let make = (~message) =>
  <header className=Style.header>
    <a href="#" onClick={_ => ReasonReactRouter.push("/decks")}>
      <img
        className=Style.logo
        src="https://cdn2.iconfinder.com/data/icons/the-joy-of-light-pi-maths-game/100/Maths-2-33-512.png"
      />
    </a>
    <div className=Style.title> {ReasonReact.string(message)} </div>
  </header>;