open Types;
type decks = Types.data(list(Types.deck));

[@react.component]
let make = () => {
  let (data, setData) = React.useState(() => Loading);
  React.useEffect0(() => {
    DecksApi.fetch(~callBack=decks => setData(_ => decks));
    None;
  });

  switch (data) {
  | Loaded(decks) =>
    decks
    |> Belt_List.map(_, deck =>
         <a key={deck.id} href={"#" ++ deck.id}>
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
  };
};