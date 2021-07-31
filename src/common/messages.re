module T = {
  type str_atom('a);

  type int_atom('a);

  type bool_atom('a);

  type float_atom('a);

  type atom('a);

  type either('a, 'b) =
    | Left('a)
    | Right('b);
};

module type S = {
  type t('a);

  type string;

  type int;

  type float;

  type bool;

  type app('a, 'b);

  include (module type of T);

  let str_atom: 'a => app(str_atom('a), string);

  let int_atom: 'a => app(int_atom('a), int);

  let bool_atom: 'a => app(bool_atom('a), bool);

  let float_atom: 'a => app(float_atom('a), float);

  /*
   (** The function [inject] allow you to insert or extract already
       typed elements values and let you manage the result by yourself.
   *)
   val inject: ('a, 'a t) app
   */

  /** [atom] gives you the possibility to hide any value inside a single value.

      let value =  Encode.atom `Str (Encode.str_atom `Str "string") in
      let value =  Encode.atom `Int (Encode.int_atom `Int 23L) in

      This is however completely untyped :

      let _ =  Decode.str_atom `Str (Decode.atom `Value value) in
      let _ =  Decode.int_atom `Int (Decode.atom `Value value) in

      If the type does not match the expected signature,
      [exception Parse_error of value * string] is raised.

  */

  let atom: 'a => app(atom('a), t('b));

  let inject: app('a, t('a));

  let list: app('a, 'b) => app(list('a), list('b));

  let pair: (app('a_, 'a), app('b_, 'b)) => app(('a_, 'b_), ('a, 'b));

  let triple:
    (app('a_, 'a), app('b_, 'b), app('c_, 'c)) =>
    app(('a_, 'b_, 'c_), ('a, 'b, 'c));

  let either: app(either('a, 'b), either(t('a), t('b)));

  let option: app('a, 'b) => app(option('a), option('b));
};
