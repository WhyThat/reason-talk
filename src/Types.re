type card = {
  id: string,
  imageUrl: option(string),
  question: string,
  answer: string,
};

type deck = {
  id: string,
  name: string,
  cards: option(list(card)),
};

type data('a) =
  | Loading
  | Error
  | Loaded('a);