open Types;

type cards = Types.data(list(Types.card));

type display =
  | Recto
  | Verso;

type status =
  | Start
  | InProgress
  | Finished;

type action =
  | SetCards(cards)
  | Finish
  | ShowAnswer
  | NextQuestion;

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
  let reducer = (state, action) =>
    switch (action) {
    | ShowAnswer => {...state, display: Verso}
    | NextQuestion => {
        ...state,
        display: Recto,
        currentIndex: state.currentIndex + 1,
      }
    | Finish => {...state, status: Finished}
    | SetCards(cards) => {...state, cards}
    };

  let (state, dispatch) = React.useReducer(reducer, initialState);
  let handleClick = React.useCallback((action, _) => dispatch(action));

  React.useEffect0(() => {
    let handleApiResult = cards => dispatch(SetCards(cards));
    let timerId =
      Utils.setTimeout(
        () => CardsApi.get(~callBack=handleApiResult, ~deckId),
        5000,
      );
    Some(() => Utils.clearTimeout(timerId));
  });

  React.useEffect1(
    () => {
      switch (state.display, state.cards) {
      | (Verso, Loaded(cards))
          when state.currentIndex == List.length(cards) - 1 =>
        dispatch(Finish)
      | _ => ()
      };
      None;
    },
    [|state.display|],
  );

  let renderButtons = (display, handleClick) =>
    switch (display) {
    | Recto =>
      <Button
        label="Show Answer"
        kind=Button.Primary
        onClick={handleClick(ShowAnswer)}
      />
    | Verso =>
      <>
        <Button
          label="Next Question"
          kind=Button.Secondary
          onClick={handleClick(NextQuestion)}
        />
        <Button
          label="Next Question"
          kind=Button.Secondary
          onClick={handleClick(NextQuestion)}
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