open BsStorybook;
open Story;

let module_ = [%bs.raw "module"];

storiesOf("Card", module_)
->addDecorator(Knobs.withKnobs)
->add("without picture", () => <Card text="Ceci est une question ?" />)
->add("with picture", () =>
    <Card
      text="Ceci est une question ? lsdjeowjdddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd"
      picture="https://media.giphy.com/media/h7QtSwBpb49MbQG2RF/giphy.gif"
    />
  );