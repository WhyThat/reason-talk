[@bs.module] external srcFromAssets: string = "../assets/loader.gif";
open BsStorybook;
open Story;

let module_ = [%bs.raw "module"];

storiesOf("Loader", module_)
->add("from gify", () => <Loader width="300" />)
->add("from asset", () => <Loader width="300" src=srcFromAssets />);