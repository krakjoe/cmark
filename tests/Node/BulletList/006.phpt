--TEST--
CommonMark\Node\BulletList Delimiter Paren
--FILE--
<?php
$list = new CommonMark\Node\BulletList;

$list->delimiter = CommonMark\Node\Lists\Delimit\Paren;

if ($list->delimiter == CommonMark\Node\Lists\Delimit\Paren) {
	echo "OK";
}
?>
--EXPECT--
OK
