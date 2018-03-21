--TEST--
CommonMark\Node\Code incorrect construction
--FILE--
<?php
try {
	new CommonMark\Node\Code([]);
} catch (TypeError $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
