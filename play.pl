my $channel = $ARGV[0];
my$previousTime=undef;
while(<STDIN>) {
	my($time, $note) = m/\((\d+) .note-on \S+ (\d+)/;
	next unless $note;

	$previousTime=$time unless $previousTime;

	my $diff = sprintf "%0.2f", $time - $previousTime;

	$previousTime=$time;

	$diff = $diff * 0.03;

	print ", release: $diff" if $diff > 0;
	print "\nsleep $diff" if $diff > 0;
	print "\nplay $note";
}

