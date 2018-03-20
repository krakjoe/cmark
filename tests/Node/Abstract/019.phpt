--TEST--
CommonMark\Node replace
--FILE--
<?php
$doc = new CommonMark\Node\Document;
$para = new CommonMark\Node\Paragraph;

$doc->appendChild($para);

$list = $para->replace(new CommonMark\Node\BulletList);

if ($list instanceof CommonMark\Node\BulletList &&
    $doc->firstChild instanceof CommonMark\Node\BulletList) {
	echo "OK";
}
?>
--EXPECT--
OK
