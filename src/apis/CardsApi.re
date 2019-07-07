open Types;

let cardDecoder = json =>
  Json.Decode.{
    id: json |> field("id", string),
    question: json |> field("question", string),
    answer: json |> field("answer", string),
    imageUrl: json |> optional(field("imageUrl", string)),
  };

let url = "http://screen-shots2.s3-us-east-2.amazonaws.com/deck";
let fetch = (~callBack, ~deckId) => {
  callBack(Loading);
  Js.Promise.(
    Fetch.fetch(url ++ string_of_int(deckId) ++ ".json")
    |> then_(Fetch.Response.json)
    |> then_(json =>
         json
         |> Json.Decode.list(cardDecoder)
         |> (cards => callBack(Loaded(cards)))
         |> resolve
       )
    |> catch(err => {
         Js.log(err);
         Js.Promise.resolve(callBack(Error));
       })
    |> ignore
  );
};