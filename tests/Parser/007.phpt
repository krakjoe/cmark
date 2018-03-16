--TEST--
CommonMark\Parser Error
--FILE--
<?php
try {
	CommonMark\Parse([]);
} catch (TypeError $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
