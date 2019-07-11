[@gentype]
type card = {
  id: string,
  imageUrl: option(string),
  question: string,
  answer: string,
};
[@gentype]
type deck = {
  id: string,
  name: string,
  cards: option(list(card)),
};
[@gentype]
type data('a) =
  | Loading
  | Error
  | Loaded('a);