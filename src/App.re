open Emotion;
global(
  "body",
  [backgroundColor(`hex("FAF9F7")), margin(px(0)), height(pct(100.))],
);
global("html", [height(pct(100.))]);
global("#root", [height(pct(100.))]);
global("*", [boxSizing(`borderBox)]);

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  switch (url.hash) {
  | deckId when String.length(deckId) > 0 =>
    <OperatingPage deckId={int_of_string(deckId)} />
  | _ => <DeckListerPage />
  };
};