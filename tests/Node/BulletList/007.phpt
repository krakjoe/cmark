--TEST--
CommonMark\Node\BulletList invalid read
--FILE--
<?php
$list = new CommonMark\Node\BulletList;

$zero = 0;

try {
	$list->$zero;
} catch (RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
