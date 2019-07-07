[@react.component]
let make =
  React.memo(() => {
    let handleClick =
      React.useCallback0((deckId, event) => {
        ReactEvent.Mouse.preventDefault(event);
        ReasonReactRouter.push("/decks/" ++ deckId);
      });
    let content =
      <ul>
        <li>
          <a href="#1" alt="access to deck1" onClick={handleClick("1")}>
            {React.string("Deck1")}
          </a>
        </li>
        <li>
          <a href="#2" alt="access to deck2" onClick={handleClick("2")}>
            {React.string("Deck2")}
          </a>
        </li>
        <li>
          <a href="#3" alt="access to deck3" onClick={handleClick("3")}>
            {React.string("Deck3")}
          </a>
        </li>
        <li>
          <a href="#4" alt="access to deck4" onClick={handleClick("4")}>
            {React.string("Deck4")}
          </a>
        </li>
        <li>
          <a href="#5" alt="access to deck5" onClick={handleClick("5")}>
            {React.string("Deck5")}
          </a>
        </li>
      </ul>;
    <Layout content />;
  });