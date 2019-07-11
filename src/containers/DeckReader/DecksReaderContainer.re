open Types;

type cards = Types.data(list(Types.card));

type display =
  | Recto
  | Verso;

type status =
  | Start
  | InProgress
  | Finished;

type difficulty =
  | Easy
  | Medium
  | Hard;

type action =
  | SetCards(cards)
  | ChangeStatus(status)
  | ShowAnswer
  | ValidateAnswer(difficulty);

type state = {
  cards,
  status,
  currentIndex: int,
  display,
};

module StartCard = {
  [@react.component]
  let make = (~onStart) =>
    <Button label="Start session \o/" onClick=onStart kind=Button.Primary />;
};

module FinishCard = {
  [@react.component]
  let make = () =>
    <>
      {React.string("Challenge Succeed well done !")}
      <Button
        label="Go back to decks"
        onClick={_ => ReasonReactRouter.push("/decks")}
        kind=Button.Primary
      />
    </>;
};

module Style = {
  open Emotion;
  let card = [%css []];
  let buttons = [%css [display(`flex), justifyContent(`spaceEvenly)]];
};

[@react.component]
let make = (~deckId, ~cards=?) => {
  let initialState = {
    cards:
      switch (cards) {
      | Some(cards) => cards
      | None => Loading
      },
    currentIndex: 0,
    display: Recto,
    status: Start,
  };
  let reducer = (state, action) =>
    switch (action) {
    | ShowAnswer => {...state, display: Verso}
    | ValidateAnswer(Hard) =>
      Js.log("This is hard !");
      {...state, display: Recto, currentIndex: state.currentIndex + 1};
    | ValidateAnswer(Medium) =>
      Js.log("This is medium !");
      {...state, display: Recto, currentIndex: state.currentIndex + 1};
    | ValidateAnswer(Easy) =>
      Js.log("This is easy !");
      {...state, display: Recto, currentIndex: state.currentIndex + 1};
    | ChangeStatus(status) => {...state, status}
    | SetCards(cards) => {...state, cards}
    };

  let (state, dispatch) = React.useReducer(reducer, initialState);
  let handleClick = React.useCallback((action, _) => dispatch(action));

  React.useEffect0(() => {
    let handleApiResult = cards => dispatch(SetCards(cards));
    let timerId =
      Utils.setTimeout(
        () =>
          switch (state.cards) {
          | Loaded(_) => ()
          | _ => CardsApi.fetch(~callBack=handleApiResult, ~deckId)
          },
        5000,
      );
    Some(() => Utils.clearTimeout(timerId));
  });

  React.useEffect1(
    () => {
      switch (state.display, state.cards) {
      | (Recto, Loaded(cards)) when state.currentIndex == List.length(cards) =>
        dispatch(ChangeStatus(Finished))
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
          label="Easy"
          kind=Button.Secondary
          onClick={handleClick(ValidateAnswer(Easy))}
        />
        <Button
          label="Medium"
          kind=Button.Secondary
          onClick={handleClick(ValidateAnswer(Medium))}
        />
        <Button
          label="Hard"
          kind=Button.Secondary
          onClick={handleClick(ValidateAnswer(Hard))}
        />
      </>
    };

  let renderCard = (display, card) =>
    switch (display, card) {
    | (Recto, Some(card)) =>
      switch (card.imageUrl) {
      | Some(url) => <Card text={card.question} picture=url />
      | None => <Card text={card.question} />
      }
    | (Verso, Some(card)) => <Card text={card.answer} />
    | _ => React.null
    };

  switch (state.cards, state.status) {
  | (Loaded(cards), InProgress) =>
    let card = Belt.List.get(cards, state.currentIndex);
    <>
      <div className=Style.card> {renderCard(state.display, card)} </div>
      <div className=Style.buttons>
        {renderButtons(state.display, handleClick)}
      </div>
    </>;
  | (_, Start) =>
    <StartCard onStart={handleClick(ChangeStatus(InProgress))} />
  | (_, Finished) => <FinishCard />
  | (Loading, _) => <Loader width="300" />
  | _ => React.null
  };
};