--TEST--
CommonMark\Render Man Error
--FILE--
<?php
try {
	CommonMark\Render\Man([]);
} catch (TypeError $ex) {
	echo "OK";
}
?>
--EXPECT--
OK

