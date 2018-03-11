--TEST--
CommonMark\Parser Finish Error
--FILE--
<?php
$parser = new CommonMark\Parser();

if ($parser->finish()) {
	echo "OK";
}
?>
--EXPECT--
OK
