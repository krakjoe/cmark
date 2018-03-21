--TEST--
CommonMark\Node\BulletList invalid write
--FILE--
<?php
$list = new CommonMark\Node\BulletList;

try {
	$list->something = "NOT OKAY";
} catch (RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
