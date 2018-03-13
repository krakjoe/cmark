--TEST--
CommonMark\Render XML Error
--FILE--
<?php
try {
	CommonMark\Render\XML([]);
} catch (TypeError $ex) {
	echo "OK";
}
?>
--EXPECT--
OK

