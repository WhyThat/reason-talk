open BsStorybook;
open Story;

let module_ = [%bs.raw "module"];

let myText =
  Knobs.text(~label="message", ~defaultValue="Hello LinkValue", ());

storiesOf("Header", module_)
->addDecorator(Knobs.withKnobs)
->add("with props", () => <Header message=myText />);