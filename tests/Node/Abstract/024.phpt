--TEST--
CommonMark\Node insertBefore used
--FILE--
<?php
$doc = new CommonMark\Node\Document;
$para = new CommonMark\Node\Paragraph;

$doc->appendChild($para);

try {
	$para->insertBefore($para);
} catch (RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
