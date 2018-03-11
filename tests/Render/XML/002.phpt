--TEST--
CommonMark\Render XML Error
--FILE--
<?php
try {
	CommonMark\Render\XML([]);
} catch (InvalidArgumentException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK

