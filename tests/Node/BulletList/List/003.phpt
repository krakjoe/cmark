--TEST--
CommonMark\Node\BulletList Delimiter Period
--FILE--
<?php
$list = new CommonMark\Node\BulletList;

$list->delimiter = CommonMark\Node\Lists\Delimit\Period;

if ($list->delimiter == CommonMark\Node\Lists\Delimit\Period) {
	echo "OK";
}
?>
--EXPECT--
OK
