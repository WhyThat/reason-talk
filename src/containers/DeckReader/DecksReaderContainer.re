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

module Style = {
  open Emotion;
  let card = [%css []];
  let buttons = [%css [display(`flex), justifyContent(`spaceEvenly)]];
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

  let handleClick =
    React.useCallback((action, _mouseEvent) => dispatch(action));

  let renderButtons = (display, handleClick) =>
    switch (display) {
    | Recto =>
      <Button
        label="Show Answer"
        kind=Button.Primary
        onClick={handleClick()}
      />
    | Verso =>
      <>
        <Button
          label="Next Question"
          kind=Button.Secondary
          onClick={handleClick()}
        />
        <Button
          label="Next Question"
          kind=Button.Secondary
          onClick={handleClick()}
        />
      </>
    };

  let renderCard = (display, card) =>
    switch (display) {
    | Recto =>
      switch (card.imageUrl) {
      | Some(url) => <Card text={card.question} picture=url />
      | None => <Card text={card.question} />
      }
    | Verso => <Card text={card.answer} />
    };

  switch (state.cards, state.status) {
  | (Loaded(cards), InProgress) =>
    let card = List.nth(cards, state.currentIndex);
    <>
      <div className=Style.card> {renderCard(state.display, card)} </div>
      <div className=Style.buttons>
        {renderButtons(state.display, handleClick)}
      </div>
    </>;
  | (_, Finished) => React.string("walouuuuuuu")
  | (Loading, _) => <Loader width="300" />
  | _ => React.null
  };
};