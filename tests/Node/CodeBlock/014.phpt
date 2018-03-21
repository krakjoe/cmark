--TEST--
CommonMark\Node\CodeBlock constructor invalid
--FILE--
<?php
try {
	$block = new CommonMark\Node\CodeBlock([]);
} catch (TypeError $ex) {
	echo "OK\n";
}
?>
--EXPECT--
OK
