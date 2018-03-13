--TEST--
CommonMark\Node\Text Bad Construct
--FILE--
<?php
try {
	new CommonMark\Node\Text([]);
} catch (TypeError $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
