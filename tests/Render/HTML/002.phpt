--TEST--
CommonMark\Render HTML Error
--FILE--
<?php
try {
	CommonMark\Render\HTML([]);
} catch (TypeError $ex) {
	echo "OK";
}
?>
--EXPECT--
OK

