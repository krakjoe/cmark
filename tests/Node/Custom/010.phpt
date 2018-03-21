--TEST--
CommonMark\Node\Custom incorrect unset
--FILE--
<?php
$block = new CommonMark\Node\CustomBlock();

$zero = 0;

try {
	unset($block->$zero);
} catch (RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
