open BsStorybook;
open Story;

let module_ = [%bs.raw "module"];

let myText = Knobs.text(~label="message", ~defaultValue="Coucou", ());

storiesOf("Component1", module_)
->addDecorator(Knobs.withKnobs)
->add("with props", () => <Component1 message=myText />);