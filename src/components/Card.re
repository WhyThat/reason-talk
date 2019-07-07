module Style = {
  open Emotion;
  let container = [%css
    [
      height(px(500)),
      padding(px(10)),
      display(flexBox),
      flexDirection(`column),
      alignItems(`center),
      justifyContent(`spaceBetween),
      border(px(1), `solid, `rgb((0, 0, 0))),
    ]
  ];
  let image = [%css [width(pct(100.))]];
  let textBlock = [%css [wordBreak(`breakAll)]];
};

[@react.component]
let make =
  React.memo((~text, ~picture=?) =>
    <div id="cardContent" className=Style.container>
      {switch (picture) {
       | Some(url) => <img src=url className=Style.image alt="picture card" />
       | None => React.null
       }}
      <div id="cardText" className=Style.textBlock>
        {ReasonReact.string(text)}
      </div>
    </div>
  );