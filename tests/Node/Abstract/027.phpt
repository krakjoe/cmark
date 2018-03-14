--TEST--
CommonMark\Node accept
--FILE--
<?php
$doc = new CommonMark\Node\Document;
$para = new CommonMark\Node\Paragraph;

$doc->appendChild($para);
$para->appendChild(
	new CommonMark\Node\Text("OK"));

$doc->accept(new class implements CommonMark\Interfaces\IVisitor {
	public function enter(CommonMark\Node $node) {
		if ($node instanceof CommonMark\Node\Text) {
			echo $node->getLiteral();
		}
	}

	public function leave(CommonMark\Node $node) {}
});
?>
--EXPECT--
OK
