--TEST--
CommonMark\Node\CodeBlock constructor extra
--FILE--
<?php
try {
	$block = new CommonMark\Node\CodeBlock("fence", "literal", "extra");
} catch (TypeError $ex) {
	echo "OK\n";
}
?>
--EXPECT--
OK
