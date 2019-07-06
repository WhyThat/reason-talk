[@react.component]
let make = (~src=?, ~width) =>
  <img
    width
    src={
      switch (src) {
      | Some(str) => str
      | None => "https://media.giphy.com/media/h7QtSwBpb49MbQG2RF/giphy.gif"
      }
    }
  />;