--TEST--
CommonMark\Node\Custom incorrect unset
--FILE--
<?php
$block = new CommonMark\Node\CustomBlock();

try {
	unset ($block->something);
} catch (RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
