open Types;

type cards = Types.data(list(Types.card));

type display =
  | Recto
  | Verso;
type status =
  | Start
  | InProgress
  | Finished;

type state = {
  cards,
  status,
  currentIndex: int,
  display,
};

[@react.component]
let make = (~deckId) => {
  let initialState = {
    cards: Loading,
    currentIndex: 0,
    display: Recto,
    status: InProgress,
  };
  let reducer = (state, action) => state;

  let (state, dispatch) = React.useReducer(reducer, initialState);

  React.null;
};