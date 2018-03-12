--TEST--
CommonMark\Parser Finish Error
--FILE--
<?php
$parser = new CommonMark\Parser();

$parser->finish();

try {
	$parser->finish();
} catch(RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
