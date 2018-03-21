--TEST--
CommonMark\Node\Custom incorrect write
--FILE--
<?php
$block = new CommonMark\Node\CustomBlock();

try {
	$block->something = "NOT OKAY";
} catch (RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
