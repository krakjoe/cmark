--TEST--
CommonMark\Parser Parse Error
--FILE--
<?php
$parser = new CommonMark\Parser();

try {
	$parser->parse([]);
} catch (TypeError $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
