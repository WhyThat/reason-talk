[@react.component]
let make =
  React.memo((~deckId) =>
    <Layout content={<DecksReaderContainer deckId />} />
  );