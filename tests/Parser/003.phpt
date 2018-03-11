--TEST--
CommonMark\Parser Parse Error
--FILE--
<?php
$parser = new CommonMark\Parser();

try {
	$parser->parse([]);
} catch (InvalidArgumentException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
