include Messages.T;

type int = Stdlib.Int64.t;
type string = Stdlib.String.t;
type float = Stdlib.Float.t;
type bool = Stdlib.Bool.t;

type t('a) = Ezjsonm.value;

type app('a, 'b) = t('a) => 'b;

let list = Ezjsonm.get_list;

let custom = (x => x, x => x);

let inject = x => x;

let str_atom = _ => Ezjsonm.get_string;

let int_atom = _ => Ezjsonm.get_int64;

let bool_atom = _ => Ezjsonm.get_bool;

let float_atom = _ => Ezjsonm.get_float;

type atom('a) = t('a);
let atom: ('a, t(atom('a))) => 'b = (
  (_, v) => v: ('a, t(atom('a))) => 'b
);

let pair = Ezjsonm.get_pair;

let triple = Ezjsonm.get_triple;

let either = t => {
  let (index, v) = Ezjsonm.get_pair(Ezjsonm.get_int, x => x, t);
  switch (index) {
  | 0 => Left(v)
  | 1 => Right(v)
  | _ => failwith("Not_found")
  };
};

let option = f =>
  fun
  | `Null => None
  | v => Some(f(v));

let process: Ezjsonm.t => t('a) = (
  fun
  | `A([value]) => value
  | `A(elems) => `A(elems)
  | `O(obj) => `O(obj):
    Ezjsonm.t => t('a)
);
