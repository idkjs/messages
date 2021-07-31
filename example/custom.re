/**
   Type definition
*/
module type Custom = {
  include Messages.S;

  let array: app('a, 'b) => app(array('a), array('b));
};

/**
   Custom encoder
*/
module EncodeArray = {
  include Messages_json.Encode;

  let array: ('a => t('b), array('a)) => t(array('b)) = (
    (f, arr) => {
      let (to_, from) = custom;
      to_(Ezjsonm.list(v => from(f(v)), Array.to_list(arr)));
    }:
      ('a => t('b), array('a)) => t(array('b))
  );
};

/**
    Custom decoder
*/
module DecodeArray = {
  include Messages_json.Decode;

  let array: (t('a) => 'b, t(array('a))) => array('b) = (
    (f, arr) => {
      let (to_, from) = custom;
      Array.of_list(Ezjsonm.get_list(v => f(from(v)), to_(arr)));
    }:
      (t('a) => 'b, t(array('a))) => array('b)
  );
};

/**
    Implementation
*/;

module Custom = (T: Custom) => {
  open T;
  let content: app(array(float_atom([ | `Prices])), _) = (
    array(float_atom(`Prices)): app(array(float_atom([ | `Prices])), _)
  );
};

module EncodeCustom = Custom(EncodeArray);

module DecodeCustom = Custom(DecodeArray);

let json': Ezjsonm.t = (
  EncodeCustom.content([|5.0, 2.0|]) |> EncodeArray.process: Ezjsonm.t
);

let () = print_endline @@ Ezjsonm.to_string(json');
