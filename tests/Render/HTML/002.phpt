--TEST--
CommonMark\Render HTML Error
--FILE--
<?php
try {
	CommonMark\Render\HTML([]);
} catch (InvalidArgumentException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK

