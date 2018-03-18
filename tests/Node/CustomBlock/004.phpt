--TEST--
CommonMark\Node\CustomBlock onEnter Error
--FILE--
<?php
$node = new CommonMark\Node\CustomBlock;

try {
	$node->setOnEnter([]);
} catch (TypeError $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
