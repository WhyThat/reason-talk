type card = {
  id: string,
  imageUrl: option(string),
  question: string,
  answer: string,
};

type deck = {
  id: string,
  name: string,
};

type data('a) =
  | Loading
  | Error
  | Loaded('a);