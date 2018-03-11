--TEST--
CommonMark\Render Man Error
--FILE--
<?php
try {
	CommonMark\Render\Man([]);
} catch (InvalidArgumentException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK

