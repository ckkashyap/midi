use std::os;
use std::io::File;



fn main() {
	let args: Vec<String> = os::args();
	let filePathString = args[1].clone();

	let path = Path::new(filePathString);


	let mut file = match File::open(&path) {
		// The `desc` field of `IoError` is a string that describes the error
		Err(why) => println!("couldn't open {}", args[1]),
		Ok(file) => println!("Hurray! "),
	};

}
