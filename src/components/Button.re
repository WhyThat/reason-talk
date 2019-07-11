type t =
  | Primary
  | Secondary;
module Style = {
  open Emotion;
  let hoverStyles = kind => [
    textDecoration(`none),
    backgroundColor(
      switch (kind) {
      | Secondary => `hex("FAFAFC")
      | Primary => `hex("40319E")
      },
    ),
    boxShadow(`transparent),
  ];
  let getBackgroundColorFromType =
    fun
    | Primary => `hex("302382")
    | Secondary => `hex("DFDFE6");
  let getColorFromType =
    fun
    | Primary => `rgb((255, 255, 255))
    | Secondary => `hex("302382");

  let button = (~kind) => [%css
    [
      padding(`px(10)),
      width(pct(100.)),
      cursor(`pointer),
      fontWeight(400),
      color(getColorFromType(kind)),
      backgroundColor(getBackgroundColorFromType(kind)),
      borderWidth(px(1)),
      borderStyle(`solid),
      textDecoration(`none),
      outline(`px(0), `none, `transparent),
      firstLetter([textTransform(`uppercase)]),
      disabled([
        color(`hex("C8C8CC")),
        borderColor(`hex("DFDFE6")),
        backgroundColor(`hex("EFEFF5")),
        boxShadow(`transparent),
        cursor(`notAllowed),
      ]),
      hover([not_("disabled", hoverStyles(kind))]),
    ]
  ];
};
[@gentype]
[@react.component]
let make = (~label, ~onClick, ~isDisabled=?, ~kind) =>
  <button
    className={Style.button(~kind)}
    onClick
    disabled={Js.Option.isSome(isDisabled)}>
    label->React.string
  </button>;