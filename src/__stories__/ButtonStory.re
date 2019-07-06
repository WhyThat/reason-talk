open BsStorybook;
open Story;
open Button;
let module_ = [%bs.raw "module"];
let clickAction = Action.action("I Clicked The Button!");
storiesOf("Button", module_)
->add("Primary disabled", () =>
    <Button
      isDisabled=true
      kind=Primary
      label="Je suis un bouton"
      onClick=clickAction
    />
  )
->add("Primary", () =>
    <Button kind=Primary label="Je suis un bouton" onClick=clickAction />
  )
->add("Secondary disabled", () =>
    <Button
      kind=Secondary
      isDisabled=true
      label="Je suis un bouton"
      onClick=clickAction
    />
  )
->add("Secondary", () =>
    <Button kind=Secondary label="Je suis un bouton" onClick=clickAction />
  );