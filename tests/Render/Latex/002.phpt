--TEST--
CommonMark\Render Latex Error
--FILE--
<?php
try {
	CommonMark\Render\Latex([]);
} catch (TypeError $ex) {
	echo "OK";
}
?>
--EXPECT--
OK

