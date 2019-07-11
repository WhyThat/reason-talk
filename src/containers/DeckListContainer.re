open Types;

[@gentype]
[@react.component]
let make = () => {
  let (cards, setCards) = React.useState(() => Loading);
  let (data, setData) = React.useState(() => Loading);
  React.useEffect0(() => {
    DecksApi.fetch(~callBack=decks => setData(_ => decks));
    None;
  });

  let handleClick = (cards, ev) => {
    switch (cards) {
    | Some(cards) =>
      ReactEvent.Mouse.preventDefault(ev);
      setCards(_ => Loaded(cards));
    | None => ()
    };
  };
  switch (cards) {
  | Loaded(_) => <DecksReaderContainer deckId=0 cards />
  | _ =>
    switch (data) {
    | Loaded(decks) =>
      decks
      |> Belt_List.map(_, deck =>
           <a
             key={deck.id}
             href={"#" ++ deck.id}
             onClick={handleClick(deck.cards)}>
             <div
               style={ReactDOMRe.Style.make(
                 ~border="1px solid black",
                 ~padding="10px",
                 (),
               )}>
               {React.string(deck.name)}
             </div>
           </a>
         )
      |> Array.of_list
      |> ReasonReact.array
    | Loading => <Loader width="300" />
    | _ => React.null
    }
  };
};