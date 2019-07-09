open Types;

let deckDecoder = json =>
  Json.Decode.{
    id: json |> field("id", string),
    name: json |> field("name", string),
  };

let url = "https://screen-shots2.s3-us-east-2.amazonaws.com/deckList.json";
let fetch = (~callBack) => {
  callBack(Loading);
  Js.Promise.(
    Fetch.fetch(url)
    |> then_(Fetch.Response.json)
    |> then_(json =>
         json
         |> Json.Decode.list(deckDecoder)
         |> (decks => callBack(Loaded(decks)))
         |> resolve
       )
    |> catch(err => {
         Js.log(err);
         Js.Promise.resolve(callBack(Error));
       })
    |> ignore
  );
};