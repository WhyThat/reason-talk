module Style = {
  open Emotion;
  let container = [%css
    [display(`flex), flexDirection(`column), height(pct(100.))]
  ];
  let content = [%css
    [
      width(`px(300)),
      margin(`auto),
      height(`pct(100.)),
      display(`flex),
      flexDirection(`column),
      alignSelf(`center),
      justifyContent(`center),
    ]
  ];
};

[@react.component]
let make = (~content) =>
  <div className=Style.container>
    <Header message="Bonjour LinkValue" />
    <div className=Style.content> content </div>
  </div>;